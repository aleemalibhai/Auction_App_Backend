import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;

public class Driver {

    /**
     * Reads the given file line by line and returns an ArrayList of Strings
     * @param fileName : (String) Name of the file
     * @return : ArrayList<String>
     */
    private static ArrayList<String> readFile(String fileName) {
        //TODO: add condition for END
        ArrayList<String> lines = new ArrayList<String>();
        try {
            File file = new File(fileName);
            if( file.exists()){
                BufferedReader r = new BufferedReader(new FileReader(file));
                String line;
                while ((line = r.readLine()) != null) {
                    lines.add(line);
                }
                r.close();
                return lines;
            }
            else{
                System.out.println("ERROR: " + fileName + " doesn't exist");
                return null;
            }

        }
        catch (IOException e) {
            System.out.println("ERROR: could not open file " + fileName);
            return null;
        }
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
            return null;
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
    public static void writeToFile(ArrayList<String> strings, String fileName){
        //TODO: deal with end
        File file = new File(fileName);
        //checking if file exists
        if(!file.exists()) {
            System.out.println("ERROR: given filename doesn't exist");
            return;
        }

        FileWriter fw = null;
        BufferedWriter bw = null;

        try{
           fw = new FileWriter(file);
           bw = new BufferedWriter(fw);

            //writing each String to the file
            for(String string: strings){
                bw.write(string + System.lineSeparator());
            }
        }
        catch (IOException e){
            System.out.println("ERROR: error in writing the file");
        }
        finally {
            if(bw != null && fw != null){
                try{
                  bw.close();
                  fw.close();
                }
                catch (IOException e){
                  System.out.println("ERROR: I/O exception" + e);
                }
            }
        }
    }

    public static void main(String[] args){
        String usersFile = ".\\resources\\users.txt";
        String itemsFile = ".\\resources\\items.txt";
        String tFile = ".\\resources\\daily_transactions.txt";

        //reading the user accounts file
        ArrayList<String> userStrings = new ArrayList<>(readFile(usersFile));;
        if (userStrings == null) {
            System.out.println("ERROR: function readFile() returned null");
            return;
        }

        //reading the available items file
        ArrayList<String> itemStrings = new ArrayList<>(readFile(itemsFile));
        if(itemStrings == null) {
            System.out.println("ERROR: function readFile() returned null");
            return;
        }

        //generating ArrayList of Users and Items
        ArrayList<User> users = getUsers(userStrings);
        ArrayList<Item> items = getItems(itemStrings);

        //read in merged transaction file
        ArrayList<String> transactions = readFile(tFile);
        if(transactions == null){
            System.out.println("ERROR: function readfile() returned null");
            return;
        }

        //reading and executing each transaction
        for(String transaction: transactions){
            //generating a Transaction object from the String
            Transaction trans = new Transaction(transaction);
            //getting the Transaction code
            String transCode = trans.getTransactionCode();

            switch(transCode){
                case("01"): //create

                    //checking is there is already a user with the given username
                    boolean constraint = false;
                    String newName = trans.get_uName();
                    for(User user: users){
                        if(newName.equals(user.getUsername())){
                            System.out.println("ERROR: <create> transaction unsuccessful; username already exists");
                            constraint = true;
                            break;
                        }
                    }

                    //checking if credit is less than 1M
                    double transactionCredit = trans.getCredits();
                    if (transactionCredit > 999999){
                        System.out.println("ERROR: <create> transaction unsuccessful; credit exceeds 999,999");
                        System.exit(-1);
                    }

                    if(constraint){ break; }

                    else{
                        //creating a new user object
                        User newUser = new User(trans.getRawString());
                        System.out.println("New user: " + newUser.getUsername() + "created");

                        //adding the new object to users
                        users.add(newUser);
                        break;
                    }

                case("02"): //delete
                    String uName = trans.get_uName();
                    User deleteUser = new User();
                    boolean found = false;
                    for(User user: users) {
                        if (uName.equals(user.getUsername())) {
                            found = true;
                            deleteUser = user;
                            break;
                        }
                    }

                    if(found){
                        //dealing with items related to the user
                        for(Item item: items){
                            //removing the items where user is the seller
                            if(item.getSellerName().equals(uName)){
                                items.remove(item);
                                System.out.println("Removed item: "+ item.getItemName()+"with seller " + uName);
                            }
                            //resetting the bid to 0 where the user has the highest bid
                            if(item.getWinningUser().equals(uName)){
                                item.setHighBid(0);
                                System.out.println("Reset the highest bid for item: "+ item.getItemName() + "to 0");
                            }
                        }
                        //removing the user
                        users.remove(deleteUser);
                        System.out.println("Removed user: " + uName);
                        break;
                    }

                    else{
                        System.out.println("ERROR: <delete> transaction unsuccessful; username:" + trans.get_uName() + "not found");
                        System.exit(-1);
                    }
                    break;


                case("03"): //advertise
                    //creating a new Item
                    Item newItem = new Item();

                    /*checking constraints*/
                    //checking max price
                    if(trans.getBid() > 999.99){
                        System.out.println("ERROR: <advertise> transaction unsuccessful, price for item exceeds $999.99");
                        System.exit(-1);
                    }

                    //checking # of days of auction
                    if(trans.getDaysLeft() > 100){
                        System.out.println("ERROR: <advertise> transaction unsuccessful; number of days is > 100");
                        System.exit(-1);
                    }

                    newItem.setItemName(trans.get_iName());
                    newItem.setSellerName(trans.get_sName());
                    newItem.setHighBid(trans.getBid());

                    //adding new item to items
                    items.add(newItem);
                    break;

                case("04")://bid
                    constraint = true;
                    //checking if item and seller name exists
                    for(Item item: items) {
                        if (item.getItemName().equals(trans.get_iName()) && item.getSellerName().equals(trans.get_sName())) {
                            constraint = false;

                            //checking is the buyer has enough found to place the bid
                            for(User user: users) {
                                if (trans.get_uName().equals(user.getUsername())) {
                                    if (user.getCredits() < trans.getBid()) {
                                        System.out.println("ERROR: <bid> transaction unsuccessful; buyer doesn't have enough credits to place the bid");
                                        System.exit(-1);
                                    }
                                }
                            }
                            //updating the bid
                            item.setHighBid(trans.getBid());
                            System.out.println("New highest bid for item: " + item.getItemName() + "is: " + item.getHighBid());
                            //updating the highest bidder
                            item.setWinningUser(trans.get_uName());
                            System.out.println("Winning user for item: " + item.getItemName() + "is: " + item.getWinningUser());
                            break;
                        }

                    }
                    if(constraint){
                        System.out.println("ERROR: <bid> transaction unsuccessful; incorrect item/seller name");
                        System.exit(-1);
                    }
                    break;

                case("05")://refund

                    boolean sellerExists = false;
                    boolean buyerExists = false;

                    for(User user: users){
                        if(trans.get_uName().equals(user.getUsername())){
                            buyerExists = true;
                        }
                        if(trans.get_sName().equals(user.getUsername()) ){
                            sellerExists = true;
                        }
                    }

                    if(sellerExists == false || buyerExists == false){
                        System.out.println("ERROR: <refund> transaction unsuccessful; seller/buyer doesn't exist");
                        System.exit(-1);
                    }

                    for(User user: users) {
                        //deducting credits from sellers's account
                        if (user.getUsername().equals(trans.get_sName())) {
                            //checking if seller has enough balance for refund
                            if (user.getCredits() < trans.getCredits()) {
                                System.out.println("ERROR: <refund> transaction unsuccessful; seller doesn't have enough credit");
                                System.exit(-1);
                                //break; ?
                            } else {
                                user.setCredits(user.getCredits() - trans.getCredits());
                                System.out.println("Deducted " + trans.getCredits() + "credits from account of seller: " + user.getUsername());
                            }
                        }
                    }
                    for(User user: users){
                        //adding credits to user's account
                        if(user.getUsername().equals(trans.get_uName())){
                            //checking if credit for user exceeds 1M
                            if( (user.getCredits() + trans.getCredits()) > 999999){
                                System.out.println("ERROR: <refund> unsuccessful; refund will result in exceeding max credit limit") ;
                                System.exit(-1);
                                //break; ?
                            }
                            else {
                                user.setCredits(user.getCredits() + trans.getCredits());
                                System.out.println("Added " + trans.getCredits() + "credits to account of buyer: " + user.getUsername());
                                break;
                            }
                        }
                    }
                    break;

                case("06")://addcredit
                    for(User user: users){
                        if(user.getUsername().equals(trans.get_uName())){

                            //checking if transfer exceeds 1k
                            if(trans.getCredits() > 1000){
                                System.out.println("ERROR: <addcredi> unsuccessful; transaction limit is 1000");
                                System.exit(-1);
                                //break; ??
                            }

                            //checking if addition of credits results in exceeding credit limit for user
                            if( (user.getCredits() + trans.getCredits()) > 999999){
                                System.out.println("ERROR: <addcredi> unsuccessful; credit limit is 1000");
                                System.exit(-1);
                                //break; ??
                            }

                            else{
                                user.setCredits(user.getCredits() + trans.getCredits());
                                System.out.println("Added " + trans.getCredits() + "credits to account of buyer: " + user.getUsername());
                                break;
                            }
                        }
                    }
                    break;

                case("00")://end of session
                    //convert all Item objects to strings
                    ArrayList<String> out_itemStrings = new ArrayList<>();
                    for(Item item: items){
                        out_itemStrings.add(item.stringify());
                    }
                    //write Strings to available items file
                    writeToFile(out_itemStrings, itemsFile);

                    //convert all User objects to strings
                    ArrayList<String> out_userStrings = new ArrayList<>();
                    for(User user: users){
                        out_userStrings.add(user.stringify());
                    }
                    //write strings to current users file
                    writeToFile(out_userStrings, usersFile);
            }
        }

    }

}



