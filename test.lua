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
--------------------------------------------------
wifi.setmode(wifi.SOFTAP)
wifi.ap.config({ssid="xxx",pwd="welcome1234"})
gpio.mode(1, gpio.OUTPUT)
srv=net.createServer(net.TCP) 
srv:listen(80,function(conn) 
    conn:on("receive", function(client,request)
        local buf = "";
        local _, _, method, path, vars = string.find(request, "([A-Z]+) (.+)?(.+) HTTP");
        if(method == nil)then 
            _, _, method, path = string.find(request, "([A-Z]+) (.+) HTTP"); 
        end
        local _GET = {}
        if (vars ~= nil)then 
            for k, v in string.gmatch(vars, "(%w+)=(%w+)&*") do 
                _GET[k] = v 
                --print(v)
                
            end 
        end
  
    end)
end)
