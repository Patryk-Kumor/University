class ProductsProvider
  attr_reader :results

  def initialize(key)
    @results = Product.all
    filter_by_key(key)
  end

  def filter_by_key(key)
    @results = if key.nil? || (key == '')
                 @results
               else
                 @results.search(key)
               end
  end
end
