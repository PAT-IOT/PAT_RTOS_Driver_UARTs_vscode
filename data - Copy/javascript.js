document.addEventListener('DOMContentLoaded', function () {
    const form = document.getElementById('configForm');

    form.addEventListener('submit', function (event) {
        event.preventDefault();

        const formData = new FormData(form);
        const jsonData = {};

        formData.forEach((value, key) => {
            if (key.endsWith("[]")) {
                const name = key.replace("[]", "");
                if (!jsonData[name]) {
                    jsonData[name] = [];
                }
                jsonData[name].push(value);
            } else {
                jsonData[key] = value;
            }
        });

        // Print the data to console (you can send it to the server here)
        console.log(jsonData);
    });
});
