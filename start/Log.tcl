# 定義 Serial Port 以及通訊設定 
set serialPort COM3: 
set iomode "9600,n,8,1" 

# 從 Serial Port 收資料 
proc GetData {channel} { 
    if {[gets $channel line] > 0} { 
        # 取得一個時間戳記 
        set now [clock seconds] 
        set timestamp [clock format $now -format {%Y/%m/%d,%H:%M:%S}] 
         
        # 在收到的資料行(line)前面加上時間戳記後印出 
        puts $timestamp,$line 
    } 
} 

# 開啟 Serial Port 
set channel [open $serialPort RDWR] 

# 設定 Serial Port 
# 預設 9600bps, no parity, 8-bit data, 1 stop bit 
fconfigure $channel -mode $iomode -blocking 0 -buffering line 

# 當 Serial Port 有資料可讀時，自動呼叫 GetData 收資料 
fileevent $channel readable [list GetData $channel] 

# 進入 Event-Loop 處理 file events 
vwait forever