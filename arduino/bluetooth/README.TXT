#===============================================#
# SLAVE: Cornflower
#===============================================#
Enter AT commands:
OK
+ROLE:0
OK
+PSWD:1234
OK
+VERSION:hc01.comV2.1
OK
+ADDR:2016:2:258365
OK
+STATE:INITIALIZED
OK
+UART:9600,0,0
OK
+NAME:Cornflower
+BIND:0:0:0
OK

#===============================================#
# MASTER: Sky
#
# Bind to Cornflower:
# AT+BIND=2016,2,258365
#
# Only allow connecting to the bound address:
# AT+CMODE=0
#===============================================#
+ROLE:1
OK
OK
+NAME:Sky
OK
+ADDR:2016:2:308006
OK

