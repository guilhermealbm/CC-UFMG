tc qdisc add dev lo root netem rate 1mbit limit 20 delay 10ms loss 10%
