clear vars;
m = readmatrix('blackbox truncated for gps path.txt');
time = m(:,1);
lat = m(:, 3);
long = m(:, 4);
%long = long*(-1);

plot(long,lat,'Color',[0 0 0]);
