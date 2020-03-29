import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;

public class Driver {
    private ArrayList<User> users = new ArrayList<>();
    private ArrayList<User> items = new ArrayList<>();
    private ArrayList<User> transactions = new ArrayList<>();

    /**
     * Reads the given file line by line and returns an ArrayList of Strings
     * @param fileName : (String) Name of the file
     * @return : ArrayList<String>
     */
    public static ArrayList<String> readFile(String fileName) {
        //TODO: add condition for END
        ArrayList<String> lines = new ArrayList<String>();
        try {
            File file = new File(fileName);
            if(file.exists()){
                BufferedReader r = new BufferedReader(new FileReader(file));
                String line;
                while ((line = r.readLine()) != null) {
                    lines.add(line);
                }
                r.close();

            }
            else{
                System.out.println("ERROR: " + fileName + " doesn't exist");
                System.exit(-1);
            }

        }
        catch (IOException e) {
            // locked file
            System.out.println("ERROR: could not open file " + fileName);
            System.exit(-2);
        }
        return lines;
    }

    /**
     * Generate ArrayList of Users from ArrayList of String
     * @param userStrings: an Arraylist<String> for user accounts
     * @return : an ArrayList<User>
     */
    protected static ArrayList<User> getUsers(ArrayList<String> userStrings) {
        ArrayList<User> users = new ArrayList<>();

        if(userStrings.isEmpty()){
            System.out.println("Error: ArrayList of string is empty");
            System.exit(-1);
        }

        for (String userString : userStrings) {
            User newUser = new User(userString);
            users.add(newUser);
        }
        return users;
    }

    /**
     * generate ArrayList of items from ArrayList of String
     * @param itemStrings: ArrayList<String>
     * @return : ArrayList<Item>
     */
    public static ArrayList<Item> getItems(ArrayList<String> itemStrings) {
        ArrayList<Item> items = new ArrayList<>();
        for (String itemString : itemStrings) {
            Item newItem = new Item(itemString);
            items.add(newItem);
        }
        return items;
    }

    /**
     * Writes the strings for ArrayList to the given file
     * @param strings: ArrayList of type: String
     * @param fileName: name of the file
     */
    public static boolean writeToFile(ArrayList<String> strings, String fileName){
        //TODO: deal with end
        File file = new File(fileName);
        //checking if file exists
        if(!file.exists()) {
            System.out.println("ERROR: given filename doesn't exist");
            return false;
        }

        try{
           BufferedWriter bw = new BufferedWriter(new FileWriter(file));

            //writing each String to the file
            // over writes the file
            for(String string: strings){
                bw.write(string + System.lineSeparator());
            }

            bw.close();
            return true;
        }
        catch (IOException e){
            System.out.println("ERROR: error in writing the file");
            return false;
        }
    }

    public static void createUser(ArrayList<User> users, String transaction) {
        Transaction trans = new Transaction(transaction);
        //checking is there is already a user with the given username
        String newName = trans.get_uName();
        for(User user: users){
            if(newName.equals(user.getUsername())){
                System.out.println("ERROR: <create> username already exists, Transaction: " + transaction);
                return;
            }
        }
        //creating a new user object
        User newUser = new User(trans.get_uName(),
                trans.getUserType(),
                trans.getCredits());

        //adding the new object to users
        users.add(newUser);
    }

    public static boolean deleteUser(ArrayList<User> users, ArrayList<Item> items, String transaction) {
        Transaction trans = new Transaction(transaction);
        User del = null;
        boolean check = false;
        String uName = trans.get_uName();
        for(User user: users) {
            if (uName.equals(user.getUsername())) {
                                //removing the user
                del = user;
                check = true;
            }
        }
        users.remove(del);
        //dealing with items related to the user
        ArrayList<Item> toRemove = new ArrayList<>();
        for(Item item: items){
            //removing the items where user is the seller
            if(item.getSellerName().equals(uName)){
                toRemove.add(item);
                // System.out.println("Removed item: "+ item.getItemName()+"with seller " + uName);
            }
            //resetting the bid to 0 where the user has the highest bid
            if(item.getWinningUser().equals(uName)){
                item.setHighBid(0.0);
                // System.out.println("Reset the highest bid for item: "+ item.getItemName() + "to 0");
            }
        }
        items.removeAll(toRemove);
        // System.out.println("Removed user: " + uName);
        if (!check) {
            System.out.println("ERROR: <delete> transaction unsuccessful; username:" + trans.get_uName() + "not found");
            return false;
        }
        return true;
    }

    public static boolean advertise(ArrayList<Item> items, String transaction) {
        Transaction trans = new Transaction(transaction);
        /*checking constraints*/
        //checking max price

        //checking # of days of auction
        if(trans.getDaysLeft() <= 0){
            System.out.println("ERROR: <advertise> transaction unsuccessful; number of days is <= 0");
            return false;
        }
        //creating a new Item
        Item newItem = new Item(trans.get_iName(),
                trans.get_sName(),
                " ",
                trans.getDaysLeft(),
                trans.getBid());

        //adding new item to items
        items.add(newItem);
        return true;
    }

    public static boolean refund(ArrayList<User> users, String transaction) {
        Transaction trans = new Transaction(transaction);


        for(User user: users) {
            if (user.getUsername().equals(trans.get_uName())){
                for (User user2 : users) {
                    if (user2.getUsername().equals(trans.get_sName())){
                        user.setCredits( user.getCredits() + trans.getCredits() );
                        user2.setCredits( user2.getCredits() - trans.getCredits() );
                        return true;
                    }
                }
                // user to get money

            }
        }
        System.out.println("Error: <refund> buyer or seller does not exist, Transaction: " + transaction);
        return false;
    }

    public static boolean bid(ArrayList<Item> items, String transaction) {
        Transaction trans = new Transaction(transaction);
        //checking if item and seller name exists
        for(Item item: items) {
            if (item.getItemName().equals(trans.get_iName()) && item.getSellerName().equals(trans.get_sName())) {
                //updating the bid
                item.setHighBid(trans.getBid());
                //updating the highest bidder
                item.setWinningUser(trans.get_uName());

                // System.out.println("New highest bid for item: " + item.getItemName() + "is: " + item.getHighBid());
                // System.out.println("Winning user for item: " + item.getItemName() + "is: " + item.getWinningUser());
                return true;
            }
        }
        System.out.println("ERROR: <bid> transaction unsuccessful; incorrect item/seller name");
        return false;
    }

    public static boolean addCredits(ArrayList<User> users, String transaction) {
        Transaction trans = new Transaction(transaction);
        for (User user : users) {
            if (user.getUsername().equals(trans.get_uName())) {
                user.setCredits( user.getCredits() + trans.getCredits() );
                return true;
            }
        }
        // fails silently
        return false;
    }

    public static void closeDay(ArrayList<User> users, ArrayList<Item> items) {
        ArrayList<Item> ended = new ArrayList<>();
        // decrement days left on all items
        for (Item item : items){
            item.setDaysLeft( item.getDaysLeft() - 1 );
            if (item.getDaysLeft() == 0) {
                // item has ended
                ended.add(item);
            } else if (item.getDaysLeft() < 0) {
                // should never happen
                System.out.println("Error <end> item: " + item.getItemName() + " has negative days left closing now");
                ended.add(item);
            }
        }
        // close ended items
        for (Item item : ended) {
            User winner = null;
            User seller = null;
            for (User user : users) {
                if (user.getUsername().equals(item.getWinningUser())){
                    winner = user;
                } else if (user.getUsername().equals(item.getSellerName())){
                    seller = user;
                }
            }
            // add money to seller
            seller.setCredits( seller.getCredits() + item.getHighBid() );
            // take money from winner
            winner.setCredits( winner.getCredits() - item.getHighBid() );
            // remove item from items list
            items.remove(item);
        }
    }

    public static boolean endSession(ArrayList<User> users, String usersFile, ArrayList<Item> items, String itemsFile) {
        //convert all Item objects to strings
        ArrayList<String> out_itemStrings = new ArrayList<>();
        for(Item item: items){
            out_itemStrings.add(item.stringify());
        }
        //convert all User objects to strings
        ArrayList<String> out_userStrings = new ArrayList<>();
        for(User user: users){
            out_userStrings.add(user.stringify());
        }
        if(!writeToFile(out_itemStrings, itemsFile) || !writeToFile(out_userStrings, usersFile)) {
            return false;
        }
        return true;
    }

    public static void main(String[] args){
        String usersFile = "resources/users.txt";
        String itemsFile = "resources/items.txt";
        String tFile = "resources/daily_transactions.txt";
        if (args.length == 4) {
            usersFile = args[1];
            itemsFile = args[2];
            tFile = args[3];
        }

        //reading the user accounts file
        ArrayList<String> userStrings = new ArrayList<>(readFile(usersFile));;
        if (userStrings.size() == 0) {
            System.out.println("ERROR: function readFile() returned null2");
            return;
        }

        //reading the available items file
        ArrayList<String> itemStrings = new ArrayList<>(readFile(itemsFile));
        if(itemStrings.size() == 0) {
            System.out.println("ERROR: function readFile() returned null1");
            return;
        }

        //generating ArrayList of Users and Items
        ArrayList<User> users = getUsers(userStrings);
        ArrayList<Item> items = getItems(itemStrings);

        //read in merged transaction file
        ArrayList<String> transactions = readFile(tFile);
        if(transactions.size() == 0){
            System.out.println("ERROR: function readfile() returned null");
            return;
        }

        //reading and executing each transaction
        for(String transaction: transactions){
            //generating a Transaction object from the String
            Transaction trans = new Transaction(transaction);
            //getting the Transaction code
            switch(transaction.substring(0, 2)){
                case("01"): // create
                    createUser(users, transaction);
                    break;
                case("02"): // delete
                    if (deleteUser(users, items, transaction)) { System.exit(-1); }
                    break;
                case("03"): // advertise
                    if (!advertise(items, transaction)) { System.exit(-1); }
                    break;
                case("04"): // bid
                    if (!bid(items, transaction)) { System.exit(-1); }
                    break;
                case("05"): // refund
                    if(!refund(users, transaction)) { System.exit(-1); }
                    break;
                case("06"): // addcredit
                    addCredits(users, transaction);
                    break;
                case("00")://end of session
                    closeDay(users, items);
                    if(!endSession(users, usersFile, items, itemsFile)) { System.exit(-1);}
                    break;
            }
        }

    }

}



