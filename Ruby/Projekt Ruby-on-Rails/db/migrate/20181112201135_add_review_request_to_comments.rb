class AddReviewRequestToComments < ActiveRecord::Migration[5.2]
  def change
    add_column :comments, :review_request, :boolean, default: false
  end
end
