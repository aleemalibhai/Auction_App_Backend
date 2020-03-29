public class Item {
    private String itemName;
    private String sellerName;
    private String winningUser;
    private int daysLeft;
    private double highBid;

    public String getItemName() {
        return itemName;
    }

    public void setItemName(String itemName) {
        this.itemName = itemName;
    }

    public String getSellerName() {
        return this.sellerName;
    }

    public void setSellerName(String sellerName) {
        this.sellerName = sellerName;
    }

    public String getWinningUser() {
        return this.winningUser;
    }

    public void setWinningUser(String winningUser) {
        this.winningUser = winningUser;
    }

    public int getDaysLeft() {
        return daysLeft;
    }

    public void setDaysLeft(int daysLeft) {
        this.daysLeft = daysLeft;
    }

    public double getHighBid() {
        return this.highBid;
    }

    public void setHighBid(double highBid) {
        this.highBid = highBid;
    }


    /**
     * parse input string to create item object
     * @param input: String
     * @return : Item object
     */
    //default constructor
    public Item(){}

    public Item(String iName, String sName, String wName, int days, double highB){
        this.itemName = iName;
        this.sellerName = sName;
        this.winningUser = wName;
        this.daysLeft = days;
        this.highBid = highB;
    }

    public Item(String input) {
        this.itemName = input.substring(0, 19).trim();
        this.sellerName = input.substring(20, 36).trim();
        this.winningUser = input.substring(36, 51).trim();
        this.daysLeft = Integer.parseInt(input.substring(52, 55));
        this.highBid = Double.parseDouble(input.substring(56));

    }

    /**
     * format object into for appropriate for writing to file
     * @param : None
     * @return : String representation of Item to be written to file
     */
    public String stringify() {
        return (String.format("%-19s", this.itemName) + ' '
                + String.format("%-15s", this.sellerName) + ' '
                + String.format("%-15s", this.winningUser) + ' '
                + String.format("%03d", this.daysLeft) + ' '
                + String.format("%06.2f", this.highBid));
    }
}
