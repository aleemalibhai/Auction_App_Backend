import org.junit.Test;

import static org.junit.Assert.assertEquals;

/** 
* User Tester. 
**/
public class UserTest {
    User testUser = new User("admin          AA 999999.45");
    /**
    *
    * Method: getUsername()
    *
    */
    @Test
    public void testGetUsername() throws Exception {
        assertEquals("admin", testUser.getUsername());
    }

    /**
    *
    * Method: getAcctType()
    *
    */
    @Test
    public void testGetAcctType() throws Exception {
        assertEquals("AA", testUser.getAcctType());
    }

    /**
    *
    * Method: getCredits()
    *
    */
    @Test
    public void testGetCredits() throws Exception {
        assertEquals(999999.45, testUser.getCredits(), 0.0);
    }

    /**
    *
    * Method: stringify()
    *
    */
    @Test
    public void testStringify() throws Exception {
        assertEquals("admin          AA 999999.45", testUser.stringify());
    }
} 
