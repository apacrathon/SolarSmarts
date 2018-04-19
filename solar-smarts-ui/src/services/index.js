const query = require('./query/query.service');

module.exports = function () {
  const app = this; // eslint-disable-line no-unused-vars
  app.configure(query);
};
