clear vars;
m = readmatrix('blackbox truncated.txt');
time = m(:,1);
lat = m(:, 3);
long = m(:, 4);
%long = long*(-1);

c = readmatrix('COORDS Matricized.TXT');
ctime = c(:,1);
clat = c(:,2);
clong = c(:,3);

plot(long,lat,'Color',[0 0 0]);
hold on;
%plot(clong,clat,'Color',[0 0.4470 0.7410]);