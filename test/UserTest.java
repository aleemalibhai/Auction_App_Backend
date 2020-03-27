import org.junit.Test;

import static org.junit.Assert.assertEquals;

/** 
* User Tester. 
**/
public class UserTest {
    String userName =       "admin          ";
    String accountType =    "AA";
    String credits =        "999999.45";

    String input = String.join(" ", userName, accountType, credits);
    User testUser = new User(input);

    @Test
    public void testSecondaryUserConstructor() throws Exception {
        User usr = new User("admin", "AA", 999999.45);
        assertEquals(testUser.stringify(), usr.stringify());
    }
    @Test
    public void testGetUsername() throws Exception {
        assertEquals("admin", testUser.getUsername());
    }

    @Test
    public void testGetAcctType() throws Exception {
        assertEquals("AA", testUser.getAcctType());
    }

    @Test
    public void testGetCredits() throws Exception {
        assertEquals(999999.45, testUser.getCredits(), 0.001);
    }

    @Test
    public void testSetCredits() throws Exception {
        User usr = new User();
        usr.setCredits(10.00);
        assertEquals(10.00, usr.getCredits(),0.001);
    }

    @Test
    public void testStringify() throws Exception {
        assertEquals(input, testUser.stringify());
    }
} 
