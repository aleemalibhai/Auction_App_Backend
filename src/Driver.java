import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.sql.SQLOutput;
import java.util.ArrayList;
import java.util.Iterator;


public class Driver {

    /**
     * Reads the given file line by line and returns an ArrayList of Strings
     * @param fileName : (String) Name of the file
     * @return : ArrayList<String>
     */
    private static ArrayList<String> readFile(String fileName) {
        ArrayList<String> lines = new ArrayList<String>();
        try {
            BufferedReader r = new BufferedReader(new FileReader(fileName));
            String line;
            while ((line = r.readLine()) != null) {
                lines.add(line);
            }
            r.close();
            return lines;
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
    private static ArrayList<User> getUsers(ArrayList<String> userStrings) {
        ArrayList<User> users = new ArrayList<>();
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

    public static void main(String[] args){
        String usersFile = "u.txt";
        String itemsFile = "i.txt";
        String tFile = "t.txt";

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
                            System.out.println("ERROR: Username constraint,  username already exists");
                            constraint = true;
                            break;
                        }
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
                    boolean found = false;
                    for(User user: users){
                        if(uName.equals(user.getUsername())) {
                            found = true;

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
                            users.remove(user);
                            System.out.println("Removed user: " + uName);
                            break;
                        }
                    }
                    if(!found){
                        System.out.println("ERROR: delete operation unsuccessful, username:" + trans.get_uName() + "not found");
                    }
                    break;

                case("03"): //advertise
                    //creating a new Item
                    Item newItem = new Item();
                    newItem.setItemName(trans.get_iName());
                    newItem.setSellerName(trans.get_sName());
                    if(trans.getDaysLeft() >= 0){
                        newItem.setDaysLeft(trans.getDaysLeft());
                    }
                    else {
                        System.out.println("ERROR: number of days left can't be negative");
                        break;
                    }
                    newItem.setHighBid(trans.getBid());

                    //adding new item to items
                    items.add(newItem);
                    break;

                case("04")://bid
                    for(Item item: items){
                        if(item.getItemName().equals(trans.get_iName()) && item.getSellerName().equals(trans.get_sName())){
                            //updating the bid
                            item.setHighBid(trans.getBid());
                            System.out.println("New highest bid for item: " + item.getItemName() + "is: " + item.getHighBid());
                            //updating the highest bidder
                            item.setWinningUser(trans.get_uName());
                            System.out.println("Winning user for item: " + item.getItemName() + "is: " + item.getWinningUser());

                            break;
                        }
                    }
                    break;

                case("05")://refund
                    for(User user: users){
                        //deducting credits from sellers's account
                        if(user.getUsername().equals(trans.get_sName())){
                            user.setCredits(user.getCredits() - trans.getCredits());
                        }
                        //adding credits to user's account
                        if(user.getUsername().equals(trans.get_uName())){
                            user.setCredits(user.getCredits() + trans.getCredits());
                        }
                    }
                    break;
            }
        }

    }
}



