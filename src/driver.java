import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;


public class driver {

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
    private static ArrayList<User> getUsers (ArrayList<String> userStrings) {
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
    public static ArrayList<Item> getItems (ArrayList<String> itemStrings) {
        ArrayList<Item> items = new ArrayList<>();
        for (String itemString : itemStrings) {
            Item newItem = new Item(itemString);
            items.add(newItem);
        }
        return items;
    }

    public static void  main(String[] args){
        String usersFile = "u.txt";
        String itemsFile = "i.txt";

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
    }
}



