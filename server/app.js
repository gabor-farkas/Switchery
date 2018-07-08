'use strict';

const express = require('express');

const app = express();

const moment = require('moment-timezone');

app.get('/time.text.bud', (request, response) => {
    response.send(moment().tz('Europe/Budapest').format('HHmm'));
});

// Start the server
const PORT = process.env.PORT || 8080;
app.listen(PORT, () => {
    console.log(`App listening on port ${PORT}`);
    console.log('Press Ctrl+C to quit.');
});