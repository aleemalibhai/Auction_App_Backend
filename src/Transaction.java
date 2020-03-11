public class Transaction {
    private String transactionCode = null;
    private String uName = null;                            // appears as UUUUUU... in the docs
    private String sName = null;                            // appears as SSSSSS... in the docs
    private String iName = null;                            // appears as IIIIII... in the docs
    private String type = null;                             // appears as TT in the docs
    private double credits;                                 // appears as CCCCCC... in the docs
    private double bid;                                     // appears as PPPPPP... in the docs
    private int daysLeft;                                   // appears as DDD in the docs

    public String getTransactionCode() {
        return transactionCode;
    }       // returns transaction code

    public String get_uName() {
        return uName;
    }                          // returns uName

    public String get_sName() {
        return sName;
    }                          // returns sName

    public String get_iName() {
        return iName;
    }                          // returns iName

    public String getType() {
        return type;
    }                             // returns Type

    public double getCredits() {
        return credits;
    }                       // returns Credits (to add or available)

    public double getBid() {
        return bid;
    }                               // returns Bid (highest or new)

    public int getDaysLeft() {
        return daysLeft;
    }                        // returns Days left in auction

    public Transaction(String input){
        // parses line from transaction file into new objects

        // parse transaction code first
        this.transactionCode = input.substring(0, 2);

        switch (this.transactionCode){
            // all with form XX_UUUUUUUUUUUUUUU_TT_CCCCCCCCC
            case ("01"):
            case ("02"):
            case ("06"):
            case ("00"):
                this.uName = input.substring(3, 18).trim();
                this.type = input.substring(19, 21);
                this.credits = Float.parseFloat(input.substring(22));
                break;
            // of form XX_UUUUUUUUUUUUUUU_SSSSSSSSSSSSSSS_CCCCCCCCC
            case ("05"):
                this.uName = input.substring(3, 18).trim();
                this.sName = input.substring(19, 34).trim();
                this.credits = Float.parseFloat(input.substring(35));
                break;
            // of form XX_IIIIIIIIIIIIIIIIIII_SSSSSSSSSSSSS_DDD_PPPPPP
            case ("03"):
                this.iName = input.substring(3, 22).trim();
                this.sName = input.substring(23, 36).trim();
                this.daysLeft = Integer.parseInt(input.substring(37, 40));
                this.bid = Float.parseFloat(input.substring(41));
                break;
            // of form XX_IIIIIIIIIIIIIIIIIII_SSSSSSSSSSSSSSS_UUUUUUUUUUUUUU_PPPPPP
            case ("04"):
                this.iName = input.substring(3, 22).trim();
                this.sName = input.substring(19, 38).trim();
                this.uName = input.substring(39, 53).trim();
                this.bid = Float.parseFloat(input.substring(54));
                break;
        }
    }


}
