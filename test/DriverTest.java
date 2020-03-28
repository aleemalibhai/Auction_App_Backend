import org.junit.Test;

import java.lang.reflect.Array;
import java.util.ArrayList;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNull;

/** 
* Driver Tester. 
*
*/ 
public class DriverTest {

    /**
    *
    * Method: getUsers(ArrayList<String> userStrings)
    *
    */
    @Test
    public void testGetUsers() throws Exception {
        //we can use this to cover loop coverage
        String userString1 = "admin          AA 999999.45";
        String userString2 = "valid_user     FS 002300.01";
        String userString3 = "reg_user       SS 001000.30";
        String userString4 = "existing_user  BS 001200.41";
        /* loop coverage */

        //zero times
        ArrayList<String> noUSer = new ArrayList<>();
        assertNull(Driver.getUsers(noUSer));

        //once
        ArrayList<String> userStrings = new ArrayList<>();
        userStrings.add(userString1);

        User testUser1 = new User(userString1);
        ArrayList<User> users = new ArrayList<>();
        users.add(testUser1);

        assertEquals(users, Driver.getUsers(userStrings));

        //twice
        userStrings.add(userString2);
        User testUser2 = new User(userString2);
        users.add(testUser2);

        assertEquals(users, Driver.getUsers(userStrings));

        //many times
        userStrings.add(userString3);
        User testUser3 = new User(userString3);
        users.add(testUser3);
        userStrings.add(userString4);
        User testUser4 = new User(userString4);
        users.add(testUser4);

        assertEquals(users, Driver.getUsers(userStrings));
    }

    /**
    *
    * Method: getItems(ArrayList<String> itemStrings)
    *
    */
    @Test
    public void testGetItems() throws Exception {
        String item = "item_name           reg_user        admin           100 000001";
        ArrayList<String> itemStrings = new ArrayList<>();
        itemStrings.add(item);

        Item testItem = new Item(item);
        ArrayList<Item> items = new ArrayList<>();
        items.add(testItem);

        assertEquals(items, Driver.getItems(itemStrings));
    }

    /**
    *
    * Method: writeToFile(ArrayList<String> strings, String fileName)
    *
    */
    @Test
    public void testWriteToFile() throws Exception {
        //decision coverage
    //TODO: Test goes here...
    }

    /**
    *
    * Method: readFile(String fileName)
    *
    */
    @Test
    public void testReadFile() throws Exception {
        //decision coverage
    //TODO: Test goes here...
    /*
    try {
       Method method = Driver.getClass().getMethod("readFile", String.class);
       method.setAccessible(true);
       method.invoke(<Object>, <Parameters>);
    } catch(NoSuchMethodException e) {
    } catch(IllegalAccessException e) {
    } catch(InvocationTargetException e) {
    }
    */
    }
} 
