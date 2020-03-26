import org.junit.Test;

import static org.junit.Assert.assertEquals;

/** 
* Transaction Tester.
*/ 
public class TransactionTest {
    Transaction bidTrans = new Transaction("04 item_name           reg_user        admin           00011");
    Transaction refundTrans = new Transaction("05 existing_user   reg_user        000100.00");
    Transaction advertiseTrans = new Transaction("03 item_name           reg_user        100 000010");
    Transaction createTrans = new Transaction("01 new_user        SS 000001.00");
    /**
    *
    * Method: getTransactionCode()
    *
    */
    @Test
    public void testGetTransactionCode() throws Exception {
        assertEquals("04", bidTrans.getTransactionCode());
    }

    /**
    *
    * Method: get_uName()
    *
    */
    @Test
    public void testGet_uName() throws Exception {
        assertEquals("admin", bidTrans.get_uName());
    }

    /**
    *
    * Method: get_sName()
    *
    */
    @Test
    public void testGet_sName() throws Exception {
        assertEquals("reg_user", bidTrans.get_sName());
    }

    /**
    *
    * Method: get_iName()
    *
    */
    @Test
    public void testGet_iName() throws Exception {
        assertEquals("item_name", bidTrans.get_iName());
    }

    /**
    *
    * Method: getType()
    *
    */
    @Test
    public void testGetType() throws Exception {
        assertEquals("04", bidTrans.getType());
    }

    /**
    *
    * Method: getCredits()
    *
    */
    @Test
    public void testGetCredits() throws Exception {
        assertEquals(100.00, refundTrans.getCredits(), 0.0);
    }

    /**
    *
    * Method: getBid()
    *
    */
    @Test
    public void testGetBid() throws Exception {
        assertEquals(11, bidTrans.getBid(), 0.0);
    }

    /**
    *
    * Method: getDaysLeft()
    *
    */
    @Test
    public void testGetDaysLeft() throws Exception {
        assertEquals(100, advertiseTrans.getDaysLeft());
    }

    /**
    *
    * Method: getRawString()
    *
    */
    @Test
    public void testGetRawString() throws Exception {
        assertEquals("new_user        SS 000001.00", createTrans.getRawString());
    }

} 
