export const addFeature = (feature) => {
    const featuresDiv = document.querySelector('.features');
    const featureDiv = document.createElement('div');

    featureDiv.classList.add('feature');

    featureDiv.innerHTML = `
        <span class="circle"></span>
        <h3>${feature.title}</h3>
        <p>${feature.text}</p>
    `;

    featuresDiv.appendChild(featureDiv);

    return;
}