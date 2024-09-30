$((): void => {
    $('.tab').on('click', function() {
        const contentId = $(this).data('content');
        $('.content').hide();
        $('#' + contentId).show();
        $('.tab').removeClass('active');
        $(this).addClass('active');
    });

    $('#search-bar').on('input', function() {
        const searchTerm = String($(this).val()).toLowerCase();
        $('.content').each(() => {
            const isVisible = $(this).text().toLowerCase().includes(searchTerm);
            $(this).toggle(isVisible);
        });
    });
});