function Regress(input, output)


filename = '3YearModelDataFinal.xlsx';
num = xlsread(filename, '', '', 'basic');

GHI = num(:,4);
temp = num(:,19);
humidity = num(:,22);
y2 = num(:,10)

X = [ones(size(humidity)), humidity, temp,GHI, humidity.*temp.*GHI];
b = regress(y2,X);    % Removes NaN data

% Extract columns from the input
% (Remove unused data from cpp interface to minimize memory load on env)
colGHI = input(:, 1);
colTemperature = input(:, 2);
colHumidity = input(:, 3);
y = input(:, 4)


X = [ones(size(colHumidity)), colHumidity, colTemperature, colGHI, colHumidity.*colTemperature.*colGHI];
output = regress(y, X)    % Removes NaN data

end