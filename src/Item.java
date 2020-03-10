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

    public Item(String input) {
        // TODO: parse input from line of file
    }

    public String stringify() {
        String str = "";
        // TODO: return string version of Item to write
        return str;
    }
}
