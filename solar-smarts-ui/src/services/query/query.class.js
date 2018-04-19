'use strict';

const config = require('../../../config/default.json');
const Sequelize = require('sequelize');
const sequelize = new Sequelize(config.dbname, config.username, config.password, {
  host: config.dbhost,
  dialect: 'mysql',
  logging: false,
  define: {
    freezeTableName: true
  }
});

class Service {
  constructor (options) {
    this.options = options || {};
  }

  find (params) {
    if (!(params.query.rawQuery.substr(0, 6).toLowerCase() == "select")) {
      throw Error("Received a restricted query. Rejecting request...");
      return Promise.reject("Your query was not processed for security reasons.");
    }
    return sequelize.query(params.query.rawQuery, { type: sequelize.QueryTypes.RAW })
      .then(result => { return [result[0]]; });
  }

  get (id, params) {
    console.log(params);
    return Promise.resolve({
      id, text: `A new message with ID: ${id}!`
    });
  }

  create (data, params) {
    if (Array.isArray(data)) {
      return Promise.all(data.map(current => this.create(current)));
    }

    return Promise.resolve(data);
  }

  update (id, data, params) {
    return Promise.resolve(data);
  }

  patch (id, data, params) {
    return Promise.resolve(data);
  }

  remove (id, params) {
    return Promise.resolve({ id });
  }
}

module.exports = function (options) {
  return new Service(options);
};

module.exports.Service = Service;
