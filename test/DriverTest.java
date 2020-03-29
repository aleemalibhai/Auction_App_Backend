import org.junit.*;
import org.junit.contrib.java.lang.system.ExpectedSystemExit;

import java.io.*;
import java.util.ArrayList;

import static org.junit.Assert.*;

/** 
* Driver Tester. 
*
*/ 
public class DriverTest {
    private final ByteArrayOutputStream outContent = new ByteArrayOutputStream();
    private final PrintStream originalOut = System.out;
    File f1 = new File("resources/emptyUsers.txt");
    File f2 = new File("resources/emptyItems.txt");
    File f3 = new File("resources/emptyTrans.txt");



    @Rule
    public final ExpectedSystemExit exit = ExpectedSystemExit.none();

    @Before
    public void init() throws Exception {
        System.setOut(new PrintStream(outContent));
        f1.createNewFile();
        f2.createNewFile();
        f3.createNewFile();
    }

    @After
    public void restoreStreams() throws Exception{
        System.setOut(originalOut);
        f1.delete();
        f2.delete();
        f3.delete();
    }

    @Test
    public void testGetUserSingleElementArray()  {
        String s = "admin          AA 999999.45";
        ArrayList<String> list = new ArrayList<>();
        list.add(s);
        User test = new User(s);

        assertEquals(test.stringify(), (Driver.getUsers(list)).get(0).stringify());
    }

    @Test
    public void testGetUsersMultipleEntries()  {
        ArrayList<String> list = new ArrayList<>();
        String s1 = "valid_user     FS 002300.01";
        String s2 = "reg_user       SS 001000.30";
        String s3 = "existing_user  BS 001200.41";
        list.add(s1);
        list.add(s2);
        list.add(s3);

        ArrayList<User> target = new ArrayList<>();
        User u1 = new User(s1);
        User u2 = new User(s2);
        User u3 = new User(s3);
        target.add(u1);
        target.add(u2);
        target.add(u3);

        ArrayList<User> actual = Driver.getUsers(list);
        for (int i = 0; i < target.size(); i++) {
            assertEquals(target.get(i).stringify(), actual.get(i).stringify());
        }
    }

    @Test
    public void testGetUsersEmptyArray()  {
        exit.expectSystemExitWithStatus(-1);
        ArrayList<String> noUSer = new ArrayList<>();
        Driver.getUsers(noUSer);
        assertEquals("Error: ArrayList of string is empty\n", outContent.toString());

        }

    @Test
    public void testGetItems()  {
        String item = "item_name           reg_user        admin           100 000001";
        ArrayList<String> itemStrings = new ArrayList<>();
        itemStrings.add(item);

        Item testItem = new Item(item);
        ArrayList<Item> items = new ArrayList<>();
        items.add(testItem);

        assertEquals(items.get(0).stringify(), Driver.getItems(itemStrings).get(0).stringify());
    }

    @Test
    public void testReadWithExistingFile()  {
        ArrayList<String> al = Driver.readFile("resources/daily_transactions.txt");
        assertEquals(0, al.size());
    }

    @Test
    public void testReadWithNonExistingFile()  {
        exit.expectSystemExitWithStatus(-1);
        ArrayList<String> al = Driver.readFile("thisobviouslydoesntexist.txt");
        assertEquals("ERROR: thisobviouslydoesntexist.txt doesn't exist\n", outContent.toString());
    }

    @Test
    public void testReadWithLockedExistingFile()  {
        exit.expectSystemExitWithStatus(-2);
        ArrayList<String> al = Driver.readFile("resources/filelocked.txt");
        assertEquals("ERROR: could not open file resources/filelocked.txt\n", outContent.toString());;
    }

    @Test
    public void testWriteToFileExistingFile()  {
        ArrayList<String> targets = new ArrayList<>();
        targets.add("test1");
        targets.add("test2");
        Driver.writeToFile(targets, "resources/outfile.txt");

        ArrayList<String> actual = new ArrayList<>();
        String line = null;

        try {
            // open input stream test.txt for reading purpose.
            BufferedReader br = new BufferedReader(new FileReader("resources/outfile.txt"));

            while ((line = br.readLine()) != null) {
                actual.add(line);
            }
        } catch(Exception e) {
            e.printStackTrace();
        }

        for (int i = 0; i < actual.size(); i++) {
            assertEquals(targets.get(i), actual.get(i));
        }
    }

    @Test
    public void testWriteToFileWithNonexistentFile()  {
        ArrayList<String> strings = new ArrayList<>();
        strings.add("test1");
        strings.add("test2");
        Driver.writeToFile(strings, "thisobviouslydoesntexist.txt");
        assertEquals("ERROR: given filename doesn't exist\n", outContent.toString());
    }

    @Test
    public void testWriteToFileWithLockedFile()  {

        ArrayList<String> strings = new ArrayList<>();
        strings.add("test1");
        strings.add("test2");
        Driver.writeToFile(strings, "resources/filelocked.txt");
        assertEquals("ERROR: error in writing the file\n", outContent.toString());
    }

    /**
     *
     * Main testing
     *
     * */

    @Test
    public void testMainWithEmptyUserFile()  {
        String[] args = {"Driver.class",
                "resources/emptyUsers.txt",
                "resources/items.txt",
                "resources/daily_transactions.txt"};
        Driver.main(args);
        assertEquals("Error: Users file is empty\n", outContent.toString());

    }

    @Test
    public void testMainWithEmptyItemFile()  {
        String[] args = {"Driver.class",
                "resources/users.txt",
                "resources/emptyItems.txt",
                "resources/daily_transactions.txt"};
        Driver.main(args);
        assertEquals("Error: Items file is empty\n", outContent.toString());
    }

    @Test
    public void testMainWithEmptyTransactionFile()  {
        String[] args = {"Driver.class",
                "resources/users.txt",
                "resources/items.txt",
                "resources/emptyTrans.txt"};
        Driver.main(args);
        assertEquals("Error: Transaction file is empty\n", outContent.toString());
    }

    @Test
    public void testCreateUserNovelUser()  {
        ArrayList<User> users = new ArrayList<>();
        String transaction = "01 UUUUUUUUUUUUUUU AA 000123.89";
        User target = new User("UUUUUUUUUUUUUUU", "AA", 123.89);
        Driver.createUser(users, transaction);

        assertEquals(1, users.size());
        assertEquals(target.stringify(), users.get(0).stringify());
    }

    @Test
    public void testCreateUserExistingUser()  {
        ArrayList<User> users = new ArrayList<>();
        users. add(new User("UUUUUUUUUUUUUUU", "AA", 123.89));
        String transaction = "01 UUUUUUUUUUUUUUU AA 000123.89";
        String err = "ERROR: <create> username already exists, Transaction: " + transaction + "\n";
        Driver.createUser(users, transaction);

        assertEquals(err, outContent.toString());
    }

    @Test
    public void testDeleteUserExistingUser()  {
        ArrayList<User> users = new ArrayList<>();
        ArrayList<Item> items = new ArrayList<>();

        users.add(new User("testu1", "AA", 15));
        items.add(new Item("testiname", "testu1", "random", 10, 10.0));
        items.add(new Item("testiname2", "random", "testu1", 10, 15.0));

        String transaction = "02 testu1          AA 000000000";
        Transaction t = new Transaction(transaction);
        System.err.println(t.get_uName());

        boolean tf = Driver.deleteUser(users, items, transaction);

        assertTrue(tf);
        assertEquals(0, users.size());
        assertEquals(1, items.size());
        // high bid on items user has highest bid should be 0
        assertEquals(0.00, items.get(0).getHighBid(), 0.001);

    }

    @Test
    public void testDeleteUserNonexistentUser()  {
        ArrayList<User> users = new ArrayList<>();
        ArrayList<Item> items = new ArrayList<>();

        users.add(new User("testu1", "AA", 15));
        items.add(new Item("testiname", "testu1", "random", 10, 10.0));
        items.add(new Item("testiname2", "random", "testu1", 10, 15.0));
        String err = "ERROR: <delete> transaction unsuccessful; username: tesu2 not found\n";
        String transaction = "02 testu2          AA 000000000";

        boolean tf = Driver.deleteUser(users, items, transaction);

        assertFalse(tf);
        assertEquals(err, outContent.toString());
        assertEquals(1, users.size());
        assertEquals(2, items.size());

    }

    @Test
    public void testAdvertiseGoodTransaction()  {
        ArrayList<Item> items = new ArrayList<>();
        String transaction = "03 IIIIIIIIIIIIIIIIIII SSSSSSSSSSSSS 010 000100";

        Item target = new Item("IIIIIIIIIIIIIIIIIII","SSSSSSSSSSSSS","",10, 100);

        boolean tf = Driver.advertise(items, transaction);

        assertTrue(tf);
        assertEquals(1, items.size());
        assertEquals(items.get(0).stringify(), target.stringify());

    }

    @Test
    public void testAdvertiseBadTransaction()  {
        ArrayList<Item> items = new ArrayList<>();
        String transaction = "03 IIIIIIIIIIIIIIIIIII SSSSSSSSSSSSS 000 000100";
        String err = "Error: <advertise> number of days <= 0, Transaction: 03 IIIIIIIIIIIIIIIIIII SSSSSSSSSSSSS 000 000100\n";

        boolean tf = Driver.advertise(items, transaction);

        assertFalse(tf);
        assertEquals(err, outContent.toString());

    }

    @Test
    public void testRefundGoodUsers()  {
        ArrayList<User> users = new ArrayList<>();
        User u1 = new User("user1", "AA", 100.25);
        User u2 = new User("user2", "AA", 100.00);
        users.add(u1);
        users.add(u2);

        String transaction = "05           user1           user2 000000050";
        boolean tf = Driver.refund(users, transaction);

        assertTrue(tf);
        assertEquals(150.25, u1.getCredits(), 0.001);
        assertEquals(50.00, u2.getCredits(), 0.001);
    }

    @Test
    public void testRefundBadUsers()  {
        ArrayList<User> users = new ArrayList<>();
        users.add(new User("user1", "AA", 100.25));
        users.add(new User("user2", "AA", 100.00));

        String transaction = "05           user3           user2 000000050";
        boolean tf = Driver.refund(users, transaction);
        String err = "Error: <refund> buyer or seller does not exist, Transaction: 05           user3           user2 000000050\n";

        assertFalse(tf);
        assertEquals(100.25, users.get(0).getCredits(), 0.001);
        assertEquals(100.00, users.get(1).getCredits(), 0.001);
        assertEquals(err, outContent.toString());
    }

    @Test
    public void testBidGoodItemGoodSeller()  {
        ArrayList<Item> items = new ArrayList<>();
        items.add(new Item("IIIIIIIIIIIIIIIIIII", "SSSSSSSSSSSSSSS", "UUUUUUUUUUUUUU", 10, 100));
        String transaction = "04 IIIIIIIIIIIIIIIIIII SSSSSSSSSSSSSSS            test 001001";

        boolean tf = Driver.bid(items, transaction);

        assertTrue(tf);
        assertEquals("test", items.get(0).getWinningUser());
        assertEquals(1001.00, items.get(0).getHighBid(), 0.001);
    }

    @Test
    public void testBidBadItemGoodSeller()  {
        ArrayList<Item> items = new ArrayList<>();
        items.add(new Item("IIIIIIIIIIIIIIIIIII", "SSSSSSSSSSSSSSS", "UUUUUUUUUUUUUU", 10, 100));
        String transaction = "04 IIIIIIIIIIIIIIIPIII SSSSSSSSSSSSSSS            test 001001";
        String err = "ERROR: <bid>  incorrect item or seller name, Transaction: 04 IIIIIIIIIIIIIIIPIII SSSSSSSSSSSSSSS            test 001001\n";

        boolean tf = Driver.bid(items, transaction);


        assertFalse(tf);
        assertEquals(err, outContent.toString());

    }

    @Test
    public void testBidGoodItemBadSeller()  {
        ArrayList<Item> items = new ArrayList<>();
        items.add(new Item("IIIIIIIIIIIIIIIIIII", "SSSSSSSSSSSSSSS", "UUUUUUUUUUUUUU", 10, 100));
        String transaction = "04 IIIIIIIIIIIIIIIIIII SSSSSSVSSSSSSSS            test 001001";
        String err = "ERROR: <bid>  incorrect item or seller name, Transaction: 04 IIIIIIIIIIIIIIIPIII SSSSSSSSSSSSSSS            test 001001\n";

        boolean tf = Driver.bid(items, transaction);


        assertFalse(tf);
        assertEquals(err, outContent.toString());

    }

    @Test
    public void testAddCreditsGoodUser()  {
        ArrayList<User> users = new ArrayList<>();
        users.add(new User("test", "AA", 1000));
        String transaction = "06 test            AA 000000012";

        boolean tf = Driver.addCredits(users, transaction);

        assertTrue(tf);
        assertEquals(1012.00, users.get(0).getCredits(), 0.001);
    }

    @Test
    public void testAddCreditsBadUser()  {
        ArrayList<User> users = new ArrayList<>();
        users.add(new User("test", "AA", 1000));
        String transaction = "06 tost            AA 000000012";

        boolean tf = Driver.addCredits(users, transaction);

        assertFalse(tf);
    }

    @Test
    public void testEndSessionGoodFiles() {
        // file io handeled by write function
        ArrayList<User> users = new ArrayList<>();
        ArrayList<Item> items = new ArrayList<>();
        users.add(new User("name", "AA", 101.00));
        items.add(new Item("iname", "sname", "", 10, 100.00));

        String ufile = "resources/test/testUsers.txt";
        String ifile = "resources/test/testItems.txt";

        boolean tf = Driver.endSession(users, ufile, items, ifile);

        assertEquals("", outContent.toString());
        assertTrue(tf);

    }

    @Test
    public void testEndSessionBadFiles() {
        // file io handeled by write function
        ArrayList<User> users = new ArrayList<>();
        ArrayList<Item> items = new ArrayList<>();
        users.add(new User("name", "AA", 101.00));
        items.add(new Item("iname", "sname", "", 10, 100.00));

        String ufile = "ufile.txt";
        String ifile = "ifile.txt";

        boolean tf = Driver.endSession(users, ufile, items, ifile);

        assertFalse(tf);

    }

    @Test
    public void testCloseDay() {
        ArrayList<User> users = new ArrayList<>();
        ArrayList<Item> items = new ArrayList<>();
        users.add(new User("name", "AA", 101.00));
        users.add(new User("name2", "AA", 100.00));
        items.add(new Item("iname", "name2", "name", 1, 100.00));

        Driver.closeDay(users, items);

        assertEquals(0, items.size());
        assertEquals(1.00, users.get(0).getCredits(), 0.001);
        assertEquals(200.00, users.get(1).getCredits(), 0.001);

    }

    @Test
    public void testCloseDayNegNumber() {
        ArrayList<User> users = new ArrayList<>();
        ArrayList<Item> items = new ArrayList<>();
        users.add(new User("name", "AA", 101.00));
        users.add(new User("name2", "AA", 100.00));
        items.add(new Item("iname", "name2", "name", -1, 100.00));
        String err = "Error <end> item: iname has negative days left closing now\n";
        Driver.closeDay(users, items);

        assertEquals(0, items.size());
        assertEquals(1.00, users.get(0).getCredits(), 0.001);
        assertEquals(200.00, users.get(1).getCredits(), 0.001);
        assertEquals(err, outContent.toString());

    }



} 
