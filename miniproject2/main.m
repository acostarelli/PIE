transfer = @(s) 134.391 * exp(-0.00427218 * s);

ard = serialport("COM7", 9600);

figure
hold on

while 1
    data = read(ard, 3, "double");
    pan    = data(1);
    tilt   = data(2);
    sensor = data(3);
    
    if pan == 0 && tilt == 0
        break
    end
    
    pan    = deg2rad(pan);
    tilt   = deg2rad(tilt);
    sensor = transfer(sensor);
    [x, y, z] = sph2cart(pan, tilt, sensor);
    plot3(x, y, z);
end

hold off