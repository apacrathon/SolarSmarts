const socket = io();
const client = feathers();

// Create the Feathers application with a `socketio` connection
client.configure(feathers.socketio(socket));
client.configure(feathers.hooks());

// Get the service for our `messages` endpoint
const messages = client.service('messages');

// Configure authentication
client.configure(feathers.authentication({
  storage: window.localStorage
}));

/*
client.authenticate({
  strategy: 'local',
    email: 'apacrathon@gmail.com',
    password: 'n!llpointer'
}).then((token) => {
  console.log('User is logged in', token);

  // At this point we have a valid token, so we can fetch restricted data.
  //messages.find().then(page => page.data.forEach(addMessage));
  //messages.on('created', addMessage);
});*/
