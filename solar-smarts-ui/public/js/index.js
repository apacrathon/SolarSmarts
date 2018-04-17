'use strict';

let serverUrl = 'https://localhost';
const feathersClient = feathers()
    .configure(feathers.rest(serverUrl).fetch(fetch));

const query = feathersClient.service('/query');

let app = angular.module('myApp', []);

app.controller('myCtrl', [
    '$scope',
    function($scope) {
        jQuery(document).ready(function(){
            query.find({
                query: {
                    rawQuery: "SELECT * from SolarSmarts.users;"
                }
            }).then(function(response) {
                $scope.$apply(() => {
                    $scope.userList = response[0];
                });
                console.log(response);
            });
        });
    }
]);