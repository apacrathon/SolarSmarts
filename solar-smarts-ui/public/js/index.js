'use strict';

let serverUrl = 'https://localhost';
const feathersClient = feathers()
    .configure(feathers.rest(serverUrl).fetch(fetch));

const query = feathersClient.service('/query');

function formatDate(date) {
    var d = new Date(date),
        month = '' + (d.getMonth() + 1),
        day = '' + d.getDate(),
        year = d.getFullYear();

    if (month.length < 2) month = '0' + month;
    if (day.length < 2) day = '0' + day;

    return [year, month, day].join('-');
}

let app = angular.module('myApp', []);

app.filter('ceilFilter', function(){
    return function(data){
        return Math.ceil(data);
    };
});

app.controller('myCtrl', [
    '$scope',
    function($scope) {
        jQuery(document).ready(function(){
            $scope.$apply(() => {
                $scope.datePicked = 0;
            });
            let todayPrediction = formatDate(new Date());
            $( function() {
                $( "#datepicker" ).datepicker({
                    changeMonth: true,
                    changeYear: true,
                    onSelect: function() {
                        todayPrediction = document.getElementById('datepicker').value;
                        populateFields(todayPrediction);
                    }
                });

                $( "#datepicker" ).datepicker( "option", "dateFormat", 'yy-mm-dd' );
            } );
            function populateFields(todayPrediction) {
                $scope.$apply(() => {
                    $scope.datePicked = 1;
                });
                let today = new Date(todayPrediction);
                today.setHours(today.getHours() + 10);
                let yesterday = new Date(today);
                let pastWeek = new Date(today);
                yesterday.setDate(today.getUTCDate() - 1);
                pastWeek.setDate(today.getUTCDate() - 6);
                let yesterdayDate = formatDate(yesterday);
                pastWeek = formatDate(pastWeek);
                console.log(pastWeek);
                console.log(yesterdayDate);
                // Current day temperature
                query.find({
                    query: {
                        rawQuery: "SELECT * FROM SolarSmarts.DarkSky WHERE (Date between '"+todayPrediction+"' AND '"+todayPrediction+" 23:59:59');"
                    }
                }).then(function(response) {
                    let irradianceSum = 0;
                    let humiditySum = 0;
                    let tempSum = 0;
                    for(var i = 0; i < response[0].length; i++) {
                        irradianceSum += response[0][i].Solar_Irradiance;
                        humiditySum += response[0][i].Humidity;
                        tempSum += response[0][i].Temperature;
                    }
                    let irradianceAvg = Math.round(irradianceSum/response[0].length);
                    let humidityAvg = Math.round(humiditySum/response[0].length);
                    let tempAvg = Math.round(tempSum/response[0].length);



                    $scope.$apply(() => {
                        $scope.irradianceAvg = irradianceAvg;
                        $scope.humidityAvg = humidityAvg;
                        $scope.tempAvg = tempAvg;
                        if(response[0].length == 0) {
                            console.log("jiro");
                            $scope.datePicked = 2;
                        }
                    });
                });
                // Current Day Graph and statistics
                query.find({
                    query: {
                        rawQuery: "SELECT P.Date as PDate, P.Temperature as PTemp, P.Humidity as PHumidity, P.Solar_Irradiance as PSolar, P.ghi as PGhi, P.Power_generated as PGenerated, N.Date as NDate, N.Solar_Irradiance as NSolar, N.Temperature as NTemp, N.Power_Generation as NGenerated FROM SolarSmarts.Prediction P, SolarSmarts.Noveda N WHERE ((P.Date = N.Date) AND P.Date between '"+todayPrediction+"' AND '"+todayPrediction+" 23:59:59') GROUP BY P.Date;"
                    }
                }).then(function(response) {
                    console.log(response);

                    let predictedEnergy = 0;
                    let actualEnergy = 0;
                    let pEnergyArr = [];
                    let aEnergyArr = [];

                    for(var i = 0; i < response[0].length; i++) {
                        predictedEnergy += response[0][i].PGenerated;
                        pEnergyArr[i] = response[0][i].PGenerated;
                        actualEnergy += response[0][i].NGenerated;
                        aEnergyArr[i] = response[0][i].NGenerated;
                        let tableTime = new Date(response[0][i].PDate);
                        response[0][i].timeOfDay = "" + tableTime.getUTCHours() + ":" + tableTime.getUTCMinutes() + "0";
                        let percentError = Math.abs((response[0][i].NGenerated-response[0][i].PGenerated)/response[0][i].NGenerated)*100;
                        percentError = percentError.toFixed(2);
                        response[0][i].percentError = percentError;
                    }
                    let maxEnergy = Math.max(Math.max(...pEnergyArr),Math.max(...aEnergyArr));
                    $scope.$apply(() => {
                        $scope.PEnergyGenerated = predictedEnergy;
                        $scope.AEnergyGenerated = actualEnergy;
                        $scope.todayPrediction = todayPrediction;
                        $scope.energyGenPredTable = response[0];

                        $scope.currentPage = 1;
                        $scope.total_show = "15";
                        $scope.numberOfPages = 10;

                        $scope.pagenumber = true;
                        $scope.totla_result_showing = true;
                        $scope.totla_result_showing_onsearcchh = false;

                        $scope.sortKey = function(key) {
                            $scope.currentPage = 1;
                            $scope.myOrderBy = key;
                        };

                        $scope.maxtotal = Math.ceil(response[0].length / parseInt($scope.total_show));
                        $scope.changeTotalShow = function(){
                            $scope.maxtotal = response[0].length / parseInt($scope.total_show);
                        };


                        var ctx = document.getElementById("myAreaChart");
                        var myLineChart = new Chart(ctx, {
                            type: 'line',
                            data: {
                                labels: ["8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18"],
                                datasets: [
                                    {
                                        label: "Predicted",
                                        lineTension: 0.3,
                                        backgroundColor: "rgba(2,117,216,0.2)",
                                        borderColor: "rgba(2,117,216,1)",
                                        pointRadius: 5,
                                        pointBackgroundColor: "rgba(2,117,216,1)",
                                        pointBorderColor: "rgba(255,255,255,0.8)",
                                        pointHoverRadius: 5,
                                        pointHoverBackgroundColor: "rgba(2,117,216,1)",
                                        pointHitRadius: 20,
                                        pointBorderWidth: 2,
                                        data: pEnergyArr,
                                    },
                                    {
                                        label: "Actual",
                                        lineTension: 0.3,
                                        backgroundColor: "rgba(216,45,2,0.2)",
                                        borderColor: "rgba(216,45,2,1)",
                                        pointRadius: 5,
                                        pointBackgroundColor: "rgba(216,45,2,1)",
                                        pointBorderColor: "rgba(216,45,2,0.8)",
                                        pointHoverRadius: 5,
                                        pointHoverBackgroundColor: "rgba(216,45,2,1)",
                                        pointHitRadius: 20,
                                        pointBorderWidth: 2,
                                        data: aEnergyArr,
                                    }
                                ],

                            },
                            options: {
                                scales: {
                                    xAxes: [{
                                        scaleLabel: {
                                            display: true,
                                            labelString: 'Hours'
                                        },
                                        time: {
                                            unit: 'date'
                                        },
                                        gridLines: {
                                            display: false
                                        },
                                        ticks: {
                                            maxTicksLimit: 13
                                        }
                                    }],
                                    yAxes: [{
                                        ticks: {
                                            min: 0,
                                            max: maxEnergy+100,
                                            maxTicksLimit: Math.ceil(maxEnergy/50)
                                        },
                                        scaleLabel: {
                                            display: true,
                                            labelString: 'kWh Produced'
                                        },
                                        gridLines: {
                                            color: "rgba(0, 0, 0, .125)",
                                        }
                                    }],
                                },
                                legend: {
                                    display: true
                                }
                            }
                        });
                    });
                });
                //Previous day
                query.find({
                    query: {
                        rawQuery: "SELECT P.Date as PDate, P.Temperature as PTemp, P.Humidity as PHumidity, P.Solar_Irradiance as PSolar, P.ghi as PGhi, P.Power_generated as PGenerated, N.Date as NDate, N.Solar_Irradiance as NSolar, N.Temperature as NTemp, N.Power_Generation as NGenerated FROM SolarSmarts.Prediction P, SolarSmarts.Noveda N WHERE ((P.Date = N.Date) AND P.Date between '"+yesterdayDate+"' AND '"+yesterdayDate+" 23:59:59') GROUP BY P.Date;"
                    }
                }).then(function(response) {
                    let predictedEnergy = 0;
                    let actualEnergy = 0;
                    let pEnergyArr = [];
                    let aEnergyArr = [];
                    for(var i = 0; i < response[0].length; i++) {
                        predictedEnergy += response[0][i].PGenerated;
                        actualEnergy += response[0][i].NGenerated;
                    }
                    let percentError = Math.abs((actualEnergy-predictedEnergy)/actualEnergy)*100;
                    percentError = percentError.toFixed(2);
                    $scope.$apply(() => {
                        $scope.pEnergyGeneratedYday = predictedEnergy;
                        $scope.aEnergyGeneratedYday = actualEnergy;
                        $scope.ydayPercentError = percentError;


                    });
                });

                query.find({
                    query: {
                        rawQuery: "SELECT P.Date as PDate, P.Temperature as PTemp, P.Humidity as PHumidity, P.Solar_Irradiance as PSolar, P.ghi as PGhi, P.Power_generated as PGenerated, N.Date as NDate, N.Solar_Irradiance as NSolar, N.Temperature as NTemp, N.Power_Generation as NGenerated FROM SolarSmarts.Prediction P, SolarSmarts.Noveda N WHERE ((P.Date = N.Date) AND P.Date between '"+pastWeek+"' AND '"+todayPrediction+" 23:59:59') GROUP BY P.Date;"
                    }
                }).then(function(response) {
                    console.log(response[0]);
                    let predictedEnergy = 0;
                    let actualEnergy = 0;
                    let pEnergyArr = [];
                    let aEnergyArr = [];
                    for(var i = 0; i < response[0].length; i++) {
                        predictedEnergy += response[0][i].PGenerated;
                        actualEnergy += response[0][i].NGenerated;
                    }
                    let percentError = Math.abs((actualEnergy-predictedEnergy)/actualEnergy)*100;
                    percentError = percentError.toFixed(2);
                    $scope.$apply(() => {
                        $scope.pEnergyGeneratedWeek = predictedEnergy;
                        $scope.aEnergyGeneratedWeek = actualEnergy;
                        $scope.pastWeekPercentError = percentError;

                    });
                });
            }





        });

    }
]);