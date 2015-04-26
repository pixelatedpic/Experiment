        i=1
        tmr.alarm(0, 100, 1, function() i=i+1
        
        if i>1022 then tmr.stop(0) tmr.wdclr() end
        pwm.setup(3,500,i)
        pwm.start(3)
        print(i)
        end)
