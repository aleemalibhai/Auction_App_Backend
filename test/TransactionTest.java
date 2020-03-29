import org.junit.After;
import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.contrib.java.lang.system.ExpectedSystemExit;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;

import static org.junit.Assert.assertEquals;

public class TransactionTest {
    private final ByteArrayOutputStream outContent = new ByteArrayOutputStream();
    private final PrintStream originalOut = System.out;

    @Before
    public void setUpStreams() {
        System.setOut(new PrintStream(outContent));
    }

    @After
    public void restoreStreams() {
        System.setOut(originalOut);
    }

    @Test
    public void test00Constructor() throws Exception {
        Transaction t = new Transaction("00                             ");
        assertEquals("00", t.getTransactionCode());
        assertEquals("               ", t.get_uName());
        assertEquals("  ", t.getUserType());
        assertEquals(0.00, t.getCredits(), 0.001);
    }

    @Test
    public void test010206Constructors() throws Exception {
        Transaction t = new Transaction("01 01testUUUUUUUUU T1 001500.00");
        assertEquals("01", t.getTransactionCode());
        assertEquals("01testUUUUUUUUU", t.get_uName());
        assertEquals("T1", t.getUserType());
        assertEquals(1500.00, t.getCredits(), 0.001);
    }

    @Test
    public void test03Constructor() throws Exception {
        Transaction t = new Transaction("03 IIIIIIIIIIIIIIIIIII SSSSSSSSSSSSS 010 0010.01");
        assertEquals("03", t.getTransactionCode());
        assertEquals("IIIIIIIIIIIIIIIIIII", t.get_iName());
        assertEquals("SSSSSSSSSSSSS", t.get_sName());
        assertEquals(10, t.getDaysLeft());
        assertEquals(10.01, t.getBid(), 0.001);
    }

    @Test
    public void test04Constructor() throws Exception {
        Transaction t = new Transaction("04 IIIIIIIIIIIIIIIIIII SSSSSSSSSSSSSSS UUUUUUUUUUUUUUU 0001.2");
        assertEquals("04", t.getTransactionCode());
        assertEquals("IIIIIIIIIIIIIIIIIII", t.get_iName());
        assertEquals("UUUUUUUUUUUUUUU", t.get_uName());
        assertEquals("SSSSSSSSSSSSSSS", t.get_sName());
        assertEquals(1.20, t.getBid(), 0.001);
    }

    @Test
    public void test05Constructor() throws Exception {
        Transaction t = new Transaction("05 UUUUUUUUUUUUUUU SSSSSSSSSSSSSSS 000000122");
        assertEquals("05", t.getTransactionCode());
        assertEquals("UUUUUUUUUUUUUUU", t.get_uName());
        assertEquals("SSSSSSSSSSSSSSS", t.get_sName());
        assertEquals(122.00, t.getCredits(), 0.001);
    }

    @Rule
    public final ExpectedSystemExit exit = ExpectedSystemExit.none();
    @Test
    public void testBadInputToConstructor() throws Exception {
        exit.expectSystemExitWithStatus(-1);
        Transaction t = new Transaction("not ok input");
        assertEquals("ERROR: bad input, no valid transaction id found\n", outContent.toString());
    }
}
