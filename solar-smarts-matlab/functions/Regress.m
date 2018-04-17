function Regress(input, output)

input = xlsread("3YearModelDataFinal.xlsx", '', '', 'basic');
% Extract columns from the input
% (Remove unused data from cpp interface to minimize memory load on env)
colGHI = input(:, 4);
colTemperature = input(:, 19);
colHumidity = input(:, 22);
y = input(:, 10);

X = [ones(size(colHumidity)), colHumidity, colTemperature, colGHI, colHumidity.*colTemperature.*colGHI];
output = regress(y, X)    % Removes NaN data

end