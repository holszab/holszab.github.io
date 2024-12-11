document.addEventListener('DOMContentLoaded', function() {
    const galleryImages = document.querySelectorAll('.gallery img');
    let currentIndex = 0;

    const showModal = (index) => {
        const src = galleryImages[index].getAttribute('src');
        const modal = document.createElement('div');
        modal.classList.add('modal');
        modal.innerHTML = `
            <div class="modal-content">
                <span class="close">&times;</span>
                <img src="${src}" alt="Gallery Image">
                <div class="navigation">
                    <span class="prev">&lt;</span>
                    <span class="next">&gt;</span>
                </div>
            </div>
        `;
        document.body.appendChild(modal);

        const closeModal = () => {
            document.body.removeChild(modal);
        };

        const showNext = () => {
            currentIndex = (currentIndex + 1) % galleryImages.length;
            modal.querySelector('img').src = galleryImages[currentIndex].getAttribute('src');
        };

        const showPrev = () => {
            currentIndex = (currentIndex - 1 + galleryImages.length) % galleryImages.length;
            modal.querySelector('img').src = galleryImages[currentIndex].getAttribute('src');
        };

        modal.querySelector('.close').addEventListener('click', closeModal);
        modal.querySelector('.next').addEventListener('click', showNext);
        modal.querySelector('.prev').addEventListener('click', showPrev);
        modal.addEventListener('click', (e) => {
            if (e.target === modal) {
                closeModal();
            }
        });
    };

    galleryImages.forEach((image, index) => {
        image.addEventListener('click', () => {
            currentIndex = index;
            showModal(currentIndex);
        });
    });
});