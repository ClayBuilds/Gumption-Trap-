clear vars;

D = readmatrix('depthlog truncated.txt');
lat = D(:,1);
lon = D(:,2);
dep = D(:,3);
dep = -1*dep;

latlin = linspace(min(lat), max(lat), 100);
lonlin = linspace(min(lon), max(lon), 100);

[LAT,LON] = meshgrid(latlin, lonlin);

DEP = griddata(lon,lat,dep, LON, LAT, 'v4');

%mesh(LAT,LON,DEP);
surf(LON,LAT,DEP);

axis tight; hold on

%plot3(lat,lon,dep,'.','MarkerSize',15, 'MarkerFaceColor','#D9FFFF');
plot3(lon,lat,dep,'.','MarkerSize',30, 'Color', [0 0 0]);
title('Depth Plot')
xlabel('Longitude');
ylabel('Latitude');
zlabel('Depth(mm)');
colorbar;