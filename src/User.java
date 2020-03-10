public class User {
    private String username;
    private String acctType;
    private double credits;


    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getAcctType() {
        return acctType;
    }

    public void setAcctType(String acctType) {
        this.acctType = acctType;
    }

    public double getCredits() {
        return credits;
    }

    public void setCredits(double credits) {
        this.credits = credits;
    }

    public User(String input){
        // parse line from file into object
        // UUUUUUUUUUUUUUU_TT_CCCCCCCCC
        //       15         2     9

        // get rid of spaces on right
        this.username = input.substring(0, 15).trim();
        this.acctType = input.substring(16, 18);
        this.credits = Double.parseDouble(input.substring(19));
    }

    public String stringify(){
        return (String.format("%-15s", this.username)
                + ' ' + this.acctType + ' '
                + String.format("%09.2f", this.credits));
    }
}
