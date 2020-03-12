public class Item {
    private String itemName;
    private String sellerName;
    private String winningUser;
    private int daysLeft;
    private float highBid;

    public String getItemName() {
        return itemName;
    }

    public void setItemName(String itemName) {
        this.itemName = itemName;
    }

    public String getSellerName() {
        return sellerName;
    }

    public void setSellerName(String sellerName) {
        this.sellerName = sellerName;
    }

    public String getWinningUser() {
        return winningUser;
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

    public float getHighBid() {
        return highBid;
    }

    public void setHighBid(float highBid) {
        this.highBid = highBid;
    }


    /**
     * parse input string to create item object
     * @param input: String
     * @return : Item object
     */
    public Item(String input) {
        this.itemName = input.substring(0, 19).trim();
        this.sellerName = input.substring(20, 36).trim();
        this.winningUser = input.substring(37, 51).trim();
        this.daysLeft = Integer.parseInt(input.substring(52, 55));
        this.highBid = Float.parseFloat(input.substring(56));

    }

    /**
     * format object into for appropriate for writing to file
     * @param : None
     * @return : String representation of Item to be written to file
     */
    public String stringify() {
        return (String.format("%-19s", this.itemName) + ' '
                + String.format("%-14s", this.sellerName) + ' '
                + String.format("%-14s", this.winningUser) + ' '
                + String.format("%03d", this.daysLeft) + ' '
                + String.format("%06.2f", this.highBid));
    }
}
