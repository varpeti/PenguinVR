local socket = require "socket"

-- szrever címe portja
local address, port = "192.168.0.23", 25565

function love.load()

    udp = socket.udp()
    
    udp:settimeout(0) --timeout nem kell
    
    udp:setpeername(address, port)
    
    math.randomseed(os.time()) 
    
    entity = tostring(math.random(99999)) -- ez az id-nk
    love.window.setTitle("Client: "..entity)

    udp:send("Hello!"..entity)
    
    t = 0 
end

function love.update(deltatime)

    repeat
        data, msg = udp:receive()

        if data then 
            
            print(data)
            udp:send("ping"..math.random(99))
        
        elseif msg ~= 'timeout' then 
            error("Network error: "..tostring(msg))
        end
    until not data 

end

function love.quit()
    local dg = string.format("%s %s $", entity, 'quit', x, y)
    udp:send(dg)  
end