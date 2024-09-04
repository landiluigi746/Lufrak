const features = [
    {
        title: "Easy to use",
        description: "Lufrak is designed to be easy to use. With a simple and intuitive interface, you can easily get your Windows 10/11 computer up and running."
    },

    {
        title: "Reliable",
        description: "Lufrak uses only tools and services that are integrated and verified by Windows (most notably winget). This ensures that our optimization techniques are safe, secure, and fully compatible with your system."
    },

    {
        title: "Transparent",
        description: "Lufrak is completely transparent. All of the code that populates the program is available for you to review on <a href='https://github.com/landiluigi746/Lufrak' target='_blank'>GitHub</a>, and you can see what's happening in the background."
    }

];

const screenshots = [
    {
        title: "Installer",
        image: "images/Installer.png",
    },

    {
        title: "Security",
        image: "images/Security.png",
    },

    {
        title: "You can also view some info on your computer!",
        image: "images/System_Info.png",
    }
];

const teamMembers = [
    {
        name: "Luigi Landi",
        image: "images/LandiLuigi.jpg",
        link: 'https://github.com/landiluigi746'
    },

    {
        name: "Francesco Gaeta",
        image: "images/GaetaFrancesco.jpg",
        link: 'https://github.com/KeKK0z'
    }
];

function addTeamMembers() {
    const teamContainer = document.querySelector(".team-members");

    teamMembers.forEach(member => {
        const memberElement = document.createElement("div");
        memberElement.innerHTML = `
            <img src="${member.image}">
            <a href="${member.link}" target="_blank"><p>${member.name}</p></a>
        `;

        teamContainer.appendChild(memberElement);
    });
}

function addFeatures() {
    const featuresContainer = document.querySelector(".features");

    features.forEach(feature => {
        const featureElement = document.createElement("div");
        featureElement.innerHTML = `
            <h3>${feature.title}</h3>
            <p>${feature.description}</p>
        `;

        featuresContainer.appendChild(featureElement);
    });
}

function addScreenshots() {
    const screenshotsContainer = document.querySelector(".screenshots");

    screenshots.forEach(screenshot => {
        const screenshotElement = document.createElement("div");
        screenshotElement.innerHTML = `
            <h3>${screenshot.title}</h3>
            <img class="screenshot" src="${screenshot.image}">
        `;

        screenshotsContainer.appendChild(screenshotElement);
    });
}

document.addEventListener("DOMContentLoaded", () => {
    addFeatures();
    addScreenshots();
    addTeamMembers();
});