# run the daily transaction file 5 times
input=$1
timeout 10 ./sim_day.sh $input
timeout 10 ./sim_day.sh $input
timeout 10 ./sim_day.sh $input
timeout 10 ./sim_day.sh $input
timeout 10 ./sim_day.sh $input
