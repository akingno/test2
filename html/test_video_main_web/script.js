// 搜索框交互
document.getElementById('search-input').addEventListener('focus', function() {
  document.getElementById('search-dropdown').style.display = 'block';
});

document.getElementById('search-input').addEventListener('blur', function() {
  document.getElementById('search-dropdown').style.display = 'none';
});
