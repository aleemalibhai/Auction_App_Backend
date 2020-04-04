# run front end 5 times
currentDate=`date +%s`
input=$1
# same input file different transaction file outputs
timeout 10 ./Auction_App/Auction_app sim/users.txt sim/items.txt sim/tFiles/daily_transactions1$currentDate.txt < $input
timeout 10 ./Auction_App/Auction_app sim/users.txt sim/items.txt sim/tFiles/daily_transactions2$currentDate.txt < $input
timeout 10 ./Auction_App/Auction_app sim/users.txt sim/items.txt sim/tFiles/daily_transactions3$currentDate.txt < $input
timeout 10 ./Auction_App/Auction_app sim/users.txt sim/items.txt sim/tFiles/daily_transactions4$currentDate.txt < $input
timeout 10 ./Auction_App/Auction_app sim/users.txt sim/items.txt sim/tFiles/daily_transactions5$currentDate.txt < $input

#run merge script
timeout 10 ./transaction_combiner.sh sim/tFiles/

# run backend
timeout 10 java Auction_App_Backend/out/production/Auction_App_Backend/Driver sim/mergedTransactionFile.txt
