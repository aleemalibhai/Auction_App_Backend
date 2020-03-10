public class User {
    private String username;
    private String acctType;
    private float credits;


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

    public float getCredits() {
        return credits;
    }

    public void setCredits(float credits) {
        this.credits = credits;
    }

    public User(String input){
        // parse line from file into object
        // TODO: write constructor
    }

    public String stringify(){
        String str = "";
        // TODO: return string version of User to write
        return str;
    }


}
