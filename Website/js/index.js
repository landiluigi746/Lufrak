import { addDev } from './dev.js';
import { addFeature } from './feature.js';

const features = [
    {
        title: 'Simple',
        text: 'Lufrak is simple to use, ideal even for the less experienced. With an intuitive interface and guided steps, optimizing your PC is quick and easy. Try it now and improve your computer’s performance in just a few clicks!'
    },

    {
        title: 'Reliable',
        text: 'Lufrak uses only processes and services that are integrated and verified by Windows. This ensures that our optimization techniques are safe, secure, and fully compatible with your system.'
    },

    {
        title: 'Transparent',
        text: 'In the Transparency section of Lufrak, our Read Me provides a comprehensive overview of all the visible and hidden steps the program takes, ensuring you are always informed about what happens behind the scenes.'
    }
];

const devs = [
    {
        name: 'Luigi Landi',
        img: 'images/landiluigi746.jpg',
        link: 'https://github.com/landiluigi746'
    },

    {
        name: 'Francesco Gaeta',
        img: 'images/francescogaeta.jpg',
        link: 'https://github.com/KeKK0z'
    }
];

document.addEventListener('DOMContentLoaded', () => {
    features.forEach(feature => addFeature(feature));
    devs.forEach(dev => addDev(dev));

    return;
});

document.addEventListener('scroll', () => {
    const items = document.querySelectorAll('.item-toanimate');
    items.forEach(item => {
        if (item.getBoundingClientRect().top < window.innerHeight) {
            item.classList.add('show-item');
        }
    });

    return;
});