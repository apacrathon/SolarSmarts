'use strict';
let serverUrl = 'https://localhost';
const feathersClient = feathers()
    .configure(feathers.rest(serverUrl).fetch(fetch));
const query = feathersClient.service('/query');
console.log("test2");
let app = angular.module('myApp', []);
/*app.filter('ceilFilter', function(){
    return function(data){
        return Math.ceil(data);
    };
});
*/

app.controller('myCtrl', [
    '$scope',
    function($scope) {
    console.log("test3");
        jQuery(document).ready(function(){
            console.log("test");
            query.find({
                query:{
                    rawQuery: "SELECT * FROM (SELECT P.Date AS PDate, P.Temperature AS PTemp, P.Humidity AS PHumidity, P.Solar_Irradiance AS PSolar,P.ghi AS PGhi, P.Power_generated AS PGenerated, N.Date AS NDate, N.Solar_Irradiance AS NSolar, N.Temperature AS NTemp, N.Power_Generation AS NGenerated, DATE(P.Date) AS pErrorDay, ((ABS(SUM(P.Power_generated) - SUM(N.Power_Generation)) / SUM(N.Power_Generation)) * 100) AS PercentError FROM SolarSmarts.Prediction P, SolarSmarts.Noveda N WHERE P.Date = N.Date GROUP BY pErrorDay) A WHERE A.PercentError > 75;"
                }
            }).then(function(response){
                console.log(response);
                $scope.response;
            });


        });
    }
]);