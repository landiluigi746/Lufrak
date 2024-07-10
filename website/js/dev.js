export const addDev = (dev) => {
    const devsDiv = document.querySelector('.devs');
    const devDiv = document.createElement('div');

    devDiv.classList.add('dev');

    devDiv.innerHTML = `
        <a href="${dev.link}" target="_blank" class="dev-link">
            <img class="dev-img" src="${dev.img}" alt="${dev.name}">
            <p class="dev-name">${dev.name}</p>
        </a>
    `;

    devsDiv.appendChild(devDiv);

    return;
}