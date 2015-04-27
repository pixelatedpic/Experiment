        i=1
        tmr.alarm(0, 100, 1, function() i=i+1
        
        if i>1022 then tmr.stop(0) tmr.wdclr() end
        pwm.setup(3,500,i)
        pwm.start(3)
        print(i)
        end)

--------------------------------------------------------------------
wifi.setmode(wifi.SOFTAP)
wifi.ap.config({ssid="xxx",pwd="welcome1234"})


                
-- A simple http client
srv=net.createServer(net.TCP) 
srv:listen(80,function(conn)
   conn:on("receive",function(conn,payload)
   print(payload) -- for debugging only

    end)
end)
