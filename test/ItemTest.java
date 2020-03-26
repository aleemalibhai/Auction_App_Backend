import org.junit.Test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertThat;

public class ItemTest {
    Item testItem = new Item("item_name           reg_user        admin           100 000001");
    /**
     *
     * Method: getItemName()
     *
     */
    @Test
    public void testGetItemName() throws Exception {
        assertEquals("item_name", testItem.getItemName());
    }

    /**
     *
     * Method: getSellerName()
     *
     */
    @Test
    public void testGetSellerName() throws Exception {
        assertEquals("reg_user", testItem.getSellerName());
    }


    /**
     *
     * Method: getWinningUser()
     *
     */
    @Test
    public void testGetWinningUser() throws Exception {
        assertEquals("admin", testItem.getWinningUser());
    }

    /**
     *
     * Method: getDaysLeft()
     *
     */
    @Test
    public void testGetDaysLeft() throws Exception {
        assertEquals(100, testItem.getDaysLeft());
    }

    /**
     *
     * Method: getHighBid()
     *
     */
    @Test
    public void testGetHighBid() throws Exception {
        assertEquals(1, testItem.getHighBid(), 0.0);
    }

    /**
     *
     * Method: stringify()
     *
     */
    @Test
    public void testStringify() throws Exception {
        assertEquals("item_name           reg_user        admin           100 000001", testItem.stringify());
    }
} 
