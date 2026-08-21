function rentVehicle(model, price) {

    const days = prompt(
        `Enter number of rental days for ${model}:`
    );

    if (!days || days <= 0) {
        alert("Please enter a valid number of days.");
        return;
    }

    const total = price * days;

    alert(
        `Booking Summary\n\n` +
        `Vehicle: ${model}\n` +
        `Rental Days: ${days}\n` +
        `Price/Day: ₹${price}\n` +
        `Total Amount: ₹${total}`
    );
}


const searchInput = document.getElementById("search");

searchInput.addEventListener("input", function () {

    const searchValue = this.value.toLowerCase();

    const cards = document.querySelectorAll(".vehicle-card");

    cards.forEach(card => {

        const vehicleName =
            card.querySelector("h3").textContent.toLowerCase();

        if (vehicleName.includes(searchValue)) {
            card.style.display = "block";
        } else {
            card.style.display = "none";
        }
    });
});