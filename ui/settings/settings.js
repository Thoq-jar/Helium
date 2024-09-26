$(document).ready(() => {
    $('.tab').click(() => {
        const contentId = $(this).data('content');
        $('.content').hide();
        $('#' + contentId).show();
        $('.tab').removeClass('active');
        $(this).addClass('active');
    });

    $('#search-bar').on('input', () => {
        const searchTerm = $(this).val().toLowerCase();
        $('.content').each(() => {
            const isVisible = $(this).text().toLowerCase().includes(searchTerm);
            $(this).toggle(isVisible);
        });
    });
});
