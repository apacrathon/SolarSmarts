const Sequelize = require('sequelize');
const config = require('../config/default.json');

module.exports = function () {
  const app = this;
  const sequelize = new Sequelize(config.dbname, config.username, config.password, {
    host: config.dbhost,
    dialect: 'mysql',
    logging: false,
    define: {
      freezeTableName: true
    }
  });

  const oldSetup = app.setup;

  app.set('sequelizeClient', sequelize);

  app.setup = function (...args) {
    const result = oldSetup.apply(this, args);

    // Set up data relationships
    const models = sequelize.models;
    Object.keys(models).forEach(name => {
      if ('associate' in models[name]) {
        models[name].associate(models);
      }
    });

    // Sync to the database

    sequelize.sync();


    return result;
  };
};
