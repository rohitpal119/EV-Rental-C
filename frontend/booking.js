const params = new URLSearchParams(window.location.search);

const vehicle = params.get("vehicle");
const price = Number(params.get("price"));

document.getElementById("vehicle").value =
    vehicle || "EV";

const daysInput = document.getElementById("days");
const totalElement = document.getElementById("total");

daysInput.addEventListener("input", function () {

    const days = Number(this.value);

    const total = days > 0 ? price * days : 0;

    totalElement.textContent =
        `₹${total.toLocaleString("en-IN")}`;
});


document.getElementById("bookingForm")
    .addEventListener("submit", function(event) {

        event.preventDefault();

        const name =
            document.getElementById("customerName").value;

        const days =
            Number(document.getElementById("days").value);

        const total = price * days;

        alert(
            `Booking Confirmed!\n\n` +
            `Customer: ${name}\n` +
            `Vehicle: ${vehicle}\n` +
            `Days: ${days}\n` +
            `Total: ₹${total.toLocaleString("en-IN")}`
        );

    });