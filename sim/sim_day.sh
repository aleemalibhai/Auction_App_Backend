# run front end multiple times
currentDate=`date +%s`
inputFolder=$1

for input in $inputFolder; do
  echo $input
  timeout 10 ./Auction_App/Auction_app sim/users.txt sim/items.txt sim/tFiles/daily_transactions1$currentDate.txt < $input
done

#run merge script
timeout 10 ./transaction_combiner.sh sim/tFiles/

# run backend
timeout 10 java Auction_App_Backend/out/production/Auction_App_Backend/Driver sim/users.txt sim/items.txt sim/mergedTransactionFile.txt
