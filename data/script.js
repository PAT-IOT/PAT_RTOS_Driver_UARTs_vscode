$(document).ready(function(){
    // Function to generate buttons for each relay channel
    function generateButtons(numChannels) {
        var buttonsContainer = $('#buttons-container');
        for (var i = 1; i <= numChannels; i++) {
            var button = $('<button>').text('Channel ' + i).attr('id', 'channel-' + i);
            buttonsContainer.append(button);
        }
    }

    // Function to send control commands to the ESP32
    function controlRelay(channel, action) {
        $.ajax({
            url: 'http://YOUR_ESP32_IP_ADDRESS/relay', // Change this to your ESP32 IP address and endpoint
            method: 'POST',
            data: { channel: channel, action: action },
            success: function(response){
                console.log(response); // Log the response for debugging
            },
            error: function(xhr, status, error){
                console.error(error); // Log any errors
            }
        });
    }

    // Generate buttons for 12 relay channels
    generateButtons(12);

    // Event handler for the relay control buttons
    $('[id^="channel"]').click(function(){
        var channel = $(this).attr('id').split('-')[1];
        controlRelay(channel, 'toggle'); // Change 'toggle' to 'on' or 'off' as needed
    });
});
