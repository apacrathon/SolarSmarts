// Initializes the `query` service on path `/query`
const createService = require('./query.class.js');
const hooks = require('./query.hooks');
const filters = require('./query.filters');

module.exports = function () {
  const app = this;
  const paginate = app.get('paginate');

  const options = {
    name: 'query',
    paginate
  };

  // Initialize our service with any options it requires
  app.use('/query', createService(options));

  // Get our initialized service so that we can register hooks and filters
  const service = app.service('query');

  service.hooks(hooks);

  if (service.filter) {
    service.filter(filters);
  }
};
