public class Transaction {
    private String transactionCode = null;
    private String uName = null;                            // appears as UUUUUU... in the docs
    private String sName = null;                            // appears as SSSSSS... in the docs
    private String iName = null;                            // appears as IIIIII... in the docs
    private String userType = null;                         // appears as TT in the docs
    private String rawString = null;                        // appears as string after XX_ in the docs
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

    public String getUserType() {
        return userType;
    }                     // returns Type

    public double getCredits() {
        return credits;
    }                       // returns Credits (to add or available)

    public double getBid() {
        return bid;
    }                                // returns Bid (highest or new)

    public int getDaysLeft() {
        return daysLeft;
    }                        // returns Days left in auction

    public Transaction(String input){
        // parses line from transaction file into new objects

        // parse transaction code first
        this.transactionCode = input.substring(0, 2);

        switch (this.transactionCode){
            case ("00"): // end of session
                this.uName = "               ";
                this.userType = "  ";
                this.credits = 0.00;
                break;
            // all with form XX_UUUUUUUUUUUUUUU_TT_CCCCCCCCC
            case ("01"): //create
            case ("02"): //delete
            case ("06"): //addcredit
                this.uName = input.substring(3, 18).trim();
                this.userType = input.substring(19, 21);
                this.credits = Float.parseFloat(input.substring(22));
                break;

            // of form XX_IIIIIIIIIIIIIIIIIII_SSSSSSSSSSSSSS_DDD_PPPPPP
            case ("03"): //advertise
                this.iName = input.substring(3, 22).trim();
                this.sName = input.substring(23, 36).trim();
                this.daysLeft = Integer.parseInt(input.substring(37, 40));
                this.bid = Double.parseDouble(input.substring(41));
                break;

            // of form XX_IIIIIIIIIIIIIIIIIII_SSSSSSSSSSSSSSS_UUUUUUUUUUUUUUU_PPPPPP
            case ("04"): //bid
                this.iName = input.substring(3, 22).trim();
                this.sName = input.substring(22, 39).trim();
                this.uName = input.substring(39, 54).trim();
                this.bid = Double.parseDouble(input.substring(54));
                break;

            // of form XX_UUUUUUUUUUUUUUU_SSSSSSSSSSSSSSS_CCCCCCCCC
            case ("05"): //refund
                this.uName = input.substring(3, 18).trim();
                this.sName = input.substring(19, 34).trim();
                this.credits = Double.parseDouble(input.substring(35));
                break;

            //checking for bad input
            default:
                System.out.println("ERROR: bad input, no valid transaction id found");
                System.exit(-1);
        }
    }


}