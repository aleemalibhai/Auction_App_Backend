import org.junit.Before;
import org.junit.Test;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertThat;

public class ItemTest {

    String itemName =       "item_name          ";
    String sellerName =     "reg_user       ";
    String winningUerName = "admin          ";
    String numDaysLeft =    "100";
    String winningBid =     "200.10";
    String input = String.join(" ", itemName, sellerName, winningUerName, numDaysLeft, winningBid);
    Item testItem = new Item(input);

    @Test
    public void testSecondaryConstructor() throws Exception{
        Item itm = new Item ("item_name", "reg_user", "admin", 100, 200.10);
        assertEquals(testItem.stringify(), itm.stringify());
    }
    @Test
    public void testGetItemName() throws Exception {
        assertEquals("item_name", testItem.getItemName());
    }

    @Test
    public void testSetItemName() throws Exception {
        Item itm = new Item();
        itm.setItemName("set");
        assertEquals("set", itm.getItemName());
    }

    @Test
    public void testGetSellerName() throws Exception {
        assertEquals("reg_user", testItem.getSellerName());
    }

    @Test
    public void testSetSellerName() throws Exception {
        Item itm = new Item();
        itm.setSellerName("sname");
        assertEquals("sname", itm.getSellerName());
    }


    @Test
    public void testGetWinningUser() throws Exception {
        assertEquals("admin", testItem.getWinningUser());
    }

    @Test
    public void testSetWinningUser() throws Exception {
        Item itm = new Item();
        itm.setWinningUser("wname");
        assertEquals("wname", itm.getWinningUser());
    }

    @Test
    public void testGetDaysLeft() throws Exception {
        assertEquals(100, testItem.getDaysLeft());
    }

    @Test
    public void testSetDaysLeft() throws Exception {
        Item itm = new Item();
        itm.setDaysLeft(15);
        assertEquals(15, itm.getDaysLeft());
    }

    @Test
    public void testGetHighBid() throws Exception {
        assertEquals(200.10, testItem.getHighBid(), 0.001);
    }

    @Test
    public void testSetHighBid() throws Exception {
        Item itm = new Item();
        itm.setHighBid(200.00);
        assertEquals(200.00, itm.getHighBid(), 0.001);
    }

    @Test
    public void testStringify() throws Exception {
        assertEquals(input, testItem.stringify());
    }
} 
