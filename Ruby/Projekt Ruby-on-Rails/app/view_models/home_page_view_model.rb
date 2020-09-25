class HomePageViewModel
  def featured_product
    Product.last
  end

  def new_products
    featured_product.nil? ? [] : Product.where.not(id: featured_product.id).order('created_at desc').first(3)
  end

  def popular_products
    Product.left_joins(:comments).group(:product_id, :id).order('count(product_id) desc, created_at desc').limit(3)
  end
end
